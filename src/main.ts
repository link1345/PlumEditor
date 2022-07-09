function Button_OpenVisualEditor(){
            
    const url = 'visual_editor.html'
    window.open(url, '_blank', 'width=300,height=300')
    console.log("open window");
    //this.eventRun("PluginLoaded",["testMessage"]);
}

//console.log(document.getElementById("top_tune"));
document.getElementById("top_tune").addEventListener("click",Button_OpenVisualEditor);