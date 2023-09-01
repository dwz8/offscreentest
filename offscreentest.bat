emcc ./offscreentest.c ^
-g3 ^
-s ALLOW_MEMORY_GROWTH=1 ^
-s ENVIRONMENT=web,worker ^
-s PTHREAD_POOL_SIZE=2 ^
-pthread ^
-sOFFSCREEN_FRAMEBUFFER ^
-s MODULARIZE=1 ^
-s "EXPORT_NAME='wasmMod'" ^
--shell-file ./offscreentest_templ.html ^
-s EXPORTED_FUNCTIONS="['_malloc','_free','_main','_canvasTest']" ^
-s EXPORTED_RUNTIME_METHODS=ccall ^
-o offscreentest.html

#-sOFFSCREENCANVAS_SUPPORT=1 ^