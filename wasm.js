
(function () {
    //wait for loading
    setTimeout(function () {
        wasmMod().then (m => {
            console.log("in wasm init");
            let i;

            for (i = 0; i<5;i++){
                setTimeout(function () {
                    m.ccall("canvasTest");
                }, (i+1)*1000);
            }
            
            console.log("in wasm exit"); //nothing for this test
        });
    }, 1000);
})();
