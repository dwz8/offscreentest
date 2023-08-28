
(function () {
    //wait for loading
    setTimeout(function () {
        wasmMod().then (m => {
            console.log("in wasm init");
            m.ccall("canvasTest");
            console.log("in wasm exit"); //nothing for this test
        });
    }, 1000);
})();
