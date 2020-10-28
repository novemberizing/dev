const path = require('path');
const webpack = require('webpack');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const MiniCssExtractPlugin = require("mini-css-extract-plugin");

const ASSET_PATH = process.env.ASSET_PATH || '/';

console.log(ASSET_PATH);

module.exports = {
    mode: 'development',
    entry: {
        app: './src/index.js'
    },
    devtool: 'cheap-module-source-map',
    devServer: {
        contentBase: path.join(__dirname, 'build'),
        hot: true,
        port: 8080,
        contentBasePublicPath: '/',
        disableHostCheck: true
    },
    module: {
        rules: [
            {
                test: /\.(js|jsx)$/,
                exclude: '/node_modules',
                use: ['babel-loader']
            },
            {
                test: /\.html$/,
                use: [
                    {
                        loader: 'html-loader',
                        options: { minimize: false }
                    }
                ]
            },
            {
                test: /\.css$/,
                use: ['style-loader', 'css-loader']
            },
            {
                test: /\.scss$/,
                use: [MiniCssExtractPlugin.loader, "css-loader", "sass-loader"]
            },
            {
                test: /\.(svg|eot|woff|woff2|ttf|png|svg|jpg|gif)$/,
                use: ['file-loader']
            }
        ]
    },
    plugins: [
        new HtmlWebpackPlugin({
            filename: 'index.html',
            template: 'static/index.html',
            inject: true
        }),
        // new HtmlWebpackPlugin({
        //     filename: 'login.html',
        //     template: 'static/login.html',
        //     inject: true
        // }),
        new webpack.HotModuleReplacementPlugin(),
        new webpack.DefinePlugin({
            'process.env.ASSET_PATH': JSON.stringify(ASSET_PATH)
        })
    ],
    output: {
        path: path.resolve(__dirname + '/build'),
        publicPath: ASSET_PATH,
        filename: "bundle.js"
    }
};