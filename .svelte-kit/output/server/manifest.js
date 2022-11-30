export const manifest = {
	appDir: "_app",
	appPath: "dylsmacropad/_app",
	assets: new Set(["favicon.png"]),
	mimeTypes: {".png":"image/png"},
	_: {
		entry: {"file":"_app/immutable/start-d4156a31.js","imports":["_app/immutable/start-d4156a31.js","_app/immutable/chunks/index-8f0aa09d.js","_app/immutable/chunks/singletons-0c9c9af9.js"],"stylesheets":[],"fonts":[]},
		nodes: [
			() => import('./nodes/0.js'),
			() => import('./nodes/1.js')
		],
		routes: [
			
		],
		matchers: async () => {
			
			return {  };
		}
	}
};
