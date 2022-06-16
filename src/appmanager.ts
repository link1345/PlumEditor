
import * as yaml from 'js-yaml';
import * as fs from 'fs';

import {EventList} from './event';
import {EditorClient} from './app';

export class AppManager {

    // あとで自作のクラスに置き換える。
	client: EditorClient;

	base_doc: Object;
	moduleList: Array<Object>;

	constructor() {

		//this.base_doc = yaml.load(fs.readFileSync('./config/base.yml', 'utf8'));

        this.client = new EditorClient();
		this.moduleList = [];
	}

	async Oneload(path: string){

		const files = await fs.promises.readdir(path);

		var pluginData = {};
		//console.log(files)

		files.forEach(file => {
			var pluginItemData = {};
			pluginItemData["config_path"] = path + "/" + file;
			pluginItemData["config"] = yaml.load(fs.readFileSync( pluginItemData["config_path"] , 'utf8'));
			pluginItemData["object"] = {};
			
            //console.log("func path: " , pluginItemData["config_path"]);

			// モジュール作業
			if ( "module" in pluginItemData["config"] && "plugin_folder" in pluginItemData["config"] ) {
				// hit!
				for( var item of pluginItemData["config"]["module"] ) {
					var func_text : string = __dirname + "/plugin/" + pluginItemData["config"]["plugin_folder"] + "/" + item ;
					//console.log("func path: " , func_text);
					pluginItemData["object"][func_text] = {}
					pluginItemData["object"][func_text]["func"] = require(func_text)["main"];
					//console.log("func: " , pluginItemData["object"][func_text] );
					pluginItemData["object"][func_text]["obj"] =  new pluginItemData["object"][func_text]["func"](this.client, pluginItemData["config"], this.base_doc) ;

				}
			}

			if( Object.keys(pluginItemData["object"]).length != 0 ){
				this.moduleList.push( pluginItemData );
			}

		});
		
		//console.log(this.moduleList)
	}

	async load(){
		var path = __dirname + "/config";
		//console.log("func path: " , path);

		await this.Oneload(path);
		//console.log( "load : ", this.moduleList );
	}


	run_func = async<T extends readonly any[]>( eventName:string, module: Object[], client: EditorClient, data:[...T] ) => {
		
		// コマンド初期化
		//if(eventName === "ready"){
		//	await this.rest.put(
		//		Routes.applicationGuildCommands(this.base_doc["CLIENT_ID"], this.base_doc["GUILD_ID"]),
		//		{ body: [] },
		//	);
		//}
		//console.log( "Event:" ,  eventName , ", module" , module);
		for(let item of module){
			
			for( let obj_key of Object.keys( item["object"] ) ){

				//console.log( "Event:" ,  eventName , ", Name:" , obj_key);
				if( item["object"][obj_key]["obj"][eventName] == null ) continue;
				try {
					//console.log("data:" , ...data);
					//console.log("start!  obj_key " , obj_key , "   eventName " , eventName, "   : " , item["object"][obj_key]["obj"][eventName] );
					( await item["object"][obj_key]["obj"][eventName](client, item["config"], ...data) );				
					//console.log("end!  obj_key " , obj_key , "   eventName " , eventName);
				
				}catch(error) {
					if (error instanceof TypeError){
						// 関数がない場合の処理
						//console.log( "TypeError  Event:" ,  eventName , ", Name:" , obj_key);
					}else{				
						console.log(error);
					}
				}
			}
		}
	}

	run(){
		const eventRun = async<T extends readonly any[]>( eventName:string, data:[...T]) => {
			const _e = async<T extends readonly any[]> (...data:[...T]) => {
				await this.run_func( eventName, this.moduleList , this.client , data);
			}
            //console.log(_e);
			this.client.on(eventName, _e );
		}
		
		//console.log( EventList ) ;
		
		for( let obj_key of Object.keys( EventList ) ){
			var eventitem = [];
			for( let item in EventList[obj_key] ){
				if( item == "Date" ){
					eventitem.push( "" );
	
				}else if( item == "string" ){
					eventitem.push( "" );
	
				}else if( item == "any" ){
					eventitem.push( "" );
	
				}else{
					eventitem.push( "" );
					//eventitem.push( require('discord.js')[EventList[obj_key][item]] );
					//console.log( EventList[obj_key] );
				}	
			}
			//console.log(obj_key , " => " , eventitem );
			eventRun(obj_key ,  eventitem );
		}
		
        this.client.Run();
		//this.client.login( this.base_doc["TOKEN"] );
	}

	async exit(){
		// 各プラグインで、終了処理を行うように指令を出す。
		await this.run_func( "exit", this.moduleList , this.client , []); 
		// Botログアウト
		//this.client.destroy();
		
		//console.log(" ---------- ボット終了するぜー！ ----------");
		//process.exit(0);
	}
}