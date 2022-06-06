import {AppManager} from './appmanager';

var app = new AppManager();

async function app_run() {
  await app.load();
  app.run();
}

process.on("SIGINT", ()=>{
	app.exit();	
});

app_run().then();