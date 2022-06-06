import { app, BrowserWindow } from 'electron';
import * as path  from 'path';


export class EventData{
    eventName: string;
    func: Function;

    constructor(eventName:string , func:Function){
        this.eventName = eventName;
        this.func = func;
    }
}

export class EditorClient{
    EventList: Array<EventData>;

    constructor(){
        this.EventList = new Array<EventData>();
    }

    eventRun = async<T extends readonly any[]>( eventName:string, data:[...T] ) => {
        for( let element of this.EventList ){
            if(eventName == element.eventName){
                console.log(element.func);
                await element.func(...data);
            }
        }
	}

    async createWindow () {
        const win = new BrowserWindow({
            width: 800,
            height: 600,
            webPreferences: {
            preload: path.join(__dirname, 'preload.js')
            }
        })

        //console.log("test message");
        this.eventRun("PluginLoaded",["testMessage"]);
        win.loadFile('index.html');
    }

    on(eventName:string, event_func:Function){
        console.log(eventName, event_func);
        this.EventList.push( new EventData(eventName, event_func) );
    }

    Run(){
        app.whenReady().then(() => {
            this.createWindow()

            app.on('activate', () => {
                if (BrowserWindow.getAllWindows().length === 0) {
                this.createWindow()
                }
            })
        })

        app.on('window-all-closed', () => {
        if (process.platform !== 'darwin') {
            app.quit()
        }
        })
    }

}