const config = {
  content: ["./src/**/*.{html,js,svelte,ts}"],

  theme: {
    extend: {
      animation: {
        fadein: "fade-in 0.2s ease-out",
      },
      keyframes: {
        "fade-in": {
          "0%": { transform: "scale(98%);", opacity: "0%" },
          "100%": { transform: "scale(100%);", opacity: "100%" },
        },
      },
    },
  },

  plugins: [],
};

module.exports = config;
