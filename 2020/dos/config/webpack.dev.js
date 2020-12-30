const path = require('path');

const TerserPlugin = require("terser-webpack-plugin");
const HtmlWebpackPlugin = require('html-webpack-plugin');
const webpack = require('webpack');

console.log(path.resolve(__dirname, '../src/module'));

module.exports = {
    target: 'web',
    entry: path.resolve(__dirname, "../src/index.js"),
    output: {
        filename: 'main.js',
        path: path.resolve(__dirname, '../docs')
    },
    performance: {
        hints: false,
        maxEntrypointSize: 512000,
        maxAssetSize: 512000
    },
    devtool: 'inline-source-map',
    module: {
        rules: [
            {
                test: /\.js$/i,
                include: [ path.resolve(__dirname, 'src') ],
                exclude: [/node_modules/],
                use: {
                    loader: 'babel-loader',
                    options: {
                        presets: ['@babel/preset-env'],
                        plugins: ['@babel/plugin-proposal-class-properties']
                    }
                }
            },
            {
				test: /\.wasm$/,
                type: 'javascript/auto',
                loader: "file-loader",
                options: {
                    name(resourcePath, resourceQuery) {
                        return '[name].[ext]';
                    }
                }
            }
        ]
    },
    resolve: {
        fallback: {
            "path": false,
            "fs": false,
            "crypto": false
        }
    },
    optimization: {
        minimize: false,
        minimizer: [
            new TerserPlugin({
                extractComments: false
            })
        ]
    },
    plugins: [
        new HtmlWebpackPlugin({
            template: 'index.html',
            inject: false
        })
    ],
    devServer: {
        contentBase: path.join(__dirname, 'docs'),
        compress: true,
        port: 9000
    }
}
