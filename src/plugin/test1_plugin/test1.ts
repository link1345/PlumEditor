import {PluginBase} from '../../plugin_base';
import {EditorClient} from '../../app';

export class main extends PluginBase{
    async PluginLoaded(client: EditorClient, config: Object, message :string){
        console.log("Hello World : " , message);
    }
}