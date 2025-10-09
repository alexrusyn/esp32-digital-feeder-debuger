const webpack = require("webpack");
const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const dotenv = require('dotenv');


const PROJECT_ROOT = process.cwd();
const port = process.env.PORT || 3000;

const PROJECT_PATHS = {
    root: PROJECT_ROOT,
    appEntry: path.join(PROJECT_ROOT, "src"),
    entry: path.join(PROJECT_ROOT, "src", "index.js"),
    output: path.join(PROJECT_ROOT, "build"),
    public: path.join(PROJECT_ROOT, "public"),
};

dotenv.config();

module.exports = ({ mode }) => ({
    mode: mode === 'production' ? 'production' : 'development',
    entry: PROJECT_PATHS.entry,
    output: {
        path: PROJECT_PATHS.output
    },
    plugins: [
        new HtmlWebpackPlugin({
            template: `${PROJECT_PATHS.public}/index.html`,
            filename: "index.html",
        }),
        new webpack.DefinePlugin({
            API_KEY: JSON.stringify(process.env.API_KEY),
        })
    ],
    devServer: {
        port,
        static: {
            directory: PROJECT_PATHS.output,
        },
        webSocketServer: false,
    },
    module: {
        rules: [
            {
                test: /\.(js|jsx)$/,
                exclude: /node_modules/,
                use: ["babel-loader"],
            },
        ],
    },
    resolve: {
        extensions: ["*", ".js", ".jsx"],
    },
});
