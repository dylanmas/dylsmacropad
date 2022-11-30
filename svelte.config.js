import preprocess from "svelte-preprocess";
import adapter from "@sveltejs/adapter-static";

const dev = "production" === "development";

/** @type {import(""@sveltejs/kit").Config} */
const config = {
  kit: {
    adapter: adapter({
      pages: "docs",
      assets: "docs",
    }),
    paths: {
      // #NOTE UNCOMMENT THIS WHEN PUBLISHING
      //base: dev ? "" : "/dylsmacropad",
    },
  },
  preprocess: [
    preprocess({
      postcss: true,
    }),
  ],
};

export default config;
