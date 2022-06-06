
import {EditorClient} from './app';

export class PluginBase {
	static classList: Object = {};
	classID : Number ;

	config: Object;
	base_doc: Object;

	name : string;

	constructor(fix_client: EditorClient, config: Object, base_doc:Object, className:string ){
		this.config = config;
		this.base_doc = base_doc;
		this.name = className;
	}

	async ready(fix_client: EditorClient, config: Object){
		//console.log("ready PluginBase!  => ", config);
		return ;
	}

	async exit(fix_client: EditorClient, config: Object){
		//console.log("exit PluginBase!  => ", config);

	}

}