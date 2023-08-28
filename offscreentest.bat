emcc ./offscreentest.c ^
-g3 ^
-s ALLOW_MEMORY_GROWTH=1 ^
-s ENVIRONMENT=web,worker ^
-pthread ^
-s PTHREAD_POOL_SIZE=1 ^
-sOFFSCREENCANVAS_SUPPORT=1 ^
-s MODULARIZE=1 ^
-s "EXPORT_NAME='wasmMod'" ^
--shell-file ./offscreentest_templ.html ^
-s EXPORTED_FUNCTIONS="['_malloc','_free','_main','_canvasTest']" ^
-s EXPORTED_RUNTIME_METHODS=ccall ^
-o offscreentest.html

#-pthread
#-s PTHREAD_POOL_SIZE=1
#-fsanitize=address ^
#-s SAFE_HEAP=1 ^
#-s ASSERTIONS=2 ^
#-sMALLOC=emmalloc-memvalidate  ^
#-sWASM_WORKERS ^
#-s SUPPORT_ERRNO=0 ^

#-DNDEBUG
#-O3 -g3
#-g4
#-s "EXPORT_NAME='wasmMod'" ^
#-s INVOKE_RUN=0 ^
#-s MODULARIZE=1 ^
#-s EXPORT_ES6=1 ^
#-s AGGRESSIVE_VARIABLE_ELIMINATION=1 ^
#-s FETCH ^
#-s "EXPORT_NAME='wasmMod'" ^
#--shell-file ./index_template.html ^

#./memblocks.c ^
