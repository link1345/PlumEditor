import { app, BrowserWindow , Menu} from 'electron';
import * as path  from 'path';

import * as lang from './language';

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

    testclicked(){
        console.log("hello test message");
    }

    constructor(){
        this.EventList = new Array<EventData>();
    }

    eventRun = async<T extends readonly any[]>( eventName:string, data:[...T] ) => {
        for( let element of this.EventList ){
            if(eventName == element.eventName){
                //console.log(element.func);
                await element.func(...data);
            }
        }
    }

    async createWindow () {
        // メニュー登録
        let template : Menu = Menu.buildFromTemplate([
            {
                label: lang.languageMethod.getLang(app, "file"),
                submenu: [
                    {click:this.testclicked, label:"上書き保存"},
                    {click:this.testclicked, label:"名前付けて保存"},
                    {role:"close", label:"閉じる"},
                ]
            }
        ]);
        Menu.setApplicationMenu(template);

        // ブラウザ表示
        const win = new BrowserWindow({
            width: 800,
            height: 600,
            webPreferences: {
            preload: path.join(__dirname, 'preload.js')
            }
        })
        //console.log("test message");
        this.eventRun("PluginLoaded",["testMessage"]);
        
        win.webContents.openDevTools()
        win.loadFile('index.html');

    }

    on(eventName:string, event_func:Function){
        //console.log(eventName, event_func);
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

            console.log("Locale : " + app.getLocale());
        })

        app.on('window-all-closed', () => {
        if (process.platform !== 'darwin') {
            app.quit()
        }
        })
    }

}