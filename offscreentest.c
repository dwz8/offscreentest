
#include <stdio.h>
#include <emscripten.h>
#include <emscripten/wasm_worker.h>
#include <emscripten/threading.h>
#include <webgl/webgl2.h>
#include <assert.h>


EMSCRIPTEN_WEBGL_CONTEXT_HANDLE	ctx;

pthread_t		thread;
int				initState		= 0;
int             threadCreated	= 0;
volatile int    drawAddr		= 0;
int				step			= 0;

static void initWebGLContext(void){
	EmscriptenWebGLContextAttributes	attrs;
	EMSCRIPTEN_RESULT					res;

	emscripten_webgl_init_context_attributes(&attrs);
	attrs.majorVersion			= 2;
	attrs.minorVersion			= 0;
	attrs.explicitSwapControl	= EM_TRUE;
	ctx = emscripten_webgl_create_context("#testCanvas", &attrs);
	assert(ctx > 0);
	res = emscripten_webgl_make_context_current(ctx);
	assert(res == EMSCRIPTEN_RESULT_SUCCESS);
	initState = 1;
}

static void draw(void) {

	if (initState) {

		glClearColor(0.0f, step * 0.1f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		EMSCRIPTEN_RESULT r = emscripten_webgl_commit_frame();
		assert(r == EMSCRIPTEN_RESULT_SUCCESS);
		emscripten_thread_sleep(20);
	}
}

static void *drawMain(void *arg) {

	//create context
	initWebGLContext();

	while (1) {
		emscripten_wasm_wait_i32((int*)&drawAddr, 1, /*timeout=*/-1);
		draw();
		emscripten_atomic_store_u32((void*)&drawAddr, 1);
	}
	return 0;
}

void canvasTest(void) {

	pthread_attr_t attr;
	int            err = 0;

	if (!emscripten_supports_offscreencanvas())
		printf("no offscreencanvas\n");
	else {
		emscripten_atomic_store_u32((void*)&drawAddr, 1);
		pthread_attr_init(&attr);
		emscripten_pthread_attr_settransferredcanvases(&attr, "#testCanvas");
		err = pthread_create(&thread, &attr, drawMain, 0);
		if (err == 0) {
			//wait a bit
			double now = emscripten_get_now();
			while (emscripten_get_now() - now < 16) /*no-op*/;

			for (int i = 0; i < 5; i++) {
				//some change in color
				step++;
				//trigger redraw
				drawAddr = 2;
				emscripten_wasm_notify((int*)&drawAddr, 1);

				now = emscripten_get_now();
				while (emscripten_get_now() - now < 16) /*no-op*/;
			}
		}
	}
}
int main(int argc,char* *argv){

	emscripten_exit_with_live_runtime();
	return 0;
}
