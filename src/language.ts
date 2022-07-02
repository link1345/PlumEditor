export const trans = {
    "ja" : {
        file:"ファイル"
    },
    "en" : {
        file:"file"
    }
}

export class languageMethod{
    static getLang(app : Electron.App, message : string){
        let text = app.getLocale();
        return trans[text.substring(0,text.indexOf("-"))][message];   
    }

}
