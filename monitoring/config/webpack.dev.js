const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const webpack = require('webpack');

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
    plugins: [
        new HtmlWebpackPlugin({
            filename: 'index.html',
            template: 'static/index.html',
            inject: true
        }),
        new HtmlWebpackPlugin({
            filename: 'login.html',
            template: 'static/login.html',
            inject: true
        }),
        new webpack.HotModuleReplacementPlugin()
    ],
    output: {
        path: undefined,
        filename: "[name].js"
    }
};