const path = require('path');

var main = {
  // enntry file
  entry: './x/js/index.js',
  // 컴파일 + 번들링된 js 파일이 저장될 경로와 이름 지정
  output: {
    path: path.resolve(__dirname, 'web/dist/js'),
    filename: 'bundle.js'
  },
  module: {
    rules: [
      {
        test: /\.js$/,
        include: [
          path.resolve(__dirname, 'x/js')
        ],
        exclude: /node_modules/,
        use: {
          loader: 'babel-loader',
          options: {
            presets: ['@babel/preset-env']
          }
        }
      }
    ]
  },
  devtool: 'source-map',
  // https://webpack.js.org/concepts/mode/#mode-development
  mode: 'development',
  devServer: {
    contentBase: path.join(__dirname, 'web'),
    compress: true,
    port: 9000
  }
};

var matrix = {
    // enntry file
    entry: './x/js/matrix.js',
    // 컴파일 + 번들링된 js 파일이 저장될 경로와 이름 지정
    output: {
      path: path.resolve(__dirname, 'web/dist/js'),
      filename: 'matrix.bundle.js'
    },
    module: {
      rules: [
        {
          test: /\.js$/,
          include: [
            path.resolve(__dirname, 'x/js/x/graphics/matrix.js'),
            path.resolve(__dirname, 'x/js/x/graphics/vector.js')
          ],
          exclude: /node_modules/,
          use: {
            loader: 'babel-loader',
            options: {
              presets: ['@babel/preset-env']
            }
          }
        }
      ]
    },
    devtool: 'source-map',
    // https://webpack.js.org/concepts/mode/#mode-development
    mode: 'development',
};

var homeworld2Worker = {
    // enntry file
    entry: './x/js/homeworld2.js',
    // 컴파일 + 번들링된 js 파일이 저장될 경로와 이름 지정
    output: {
      path: path.resolve(__dirname, 'web/dist/js'),
      filename: 'homeworld2.worker.bundle.js'
    },
    module: {
      rules: [
        {
          test: /\.js$/,
          include: [
            path.resolve(__dirname, 'x/js/homeworld2/goblinmesh.js'),
            path.resolve(__dirname, 'x/js/homeworld2/joint.js'),
            path.resolve(__dirname, 'x/js/homeworld2/multimesh.js'),
            path.resolve(__dirname, 'x/js/homeworld2/obj.js'),
            path.resolve(__dirname, 'x/js/homeworld2/singlemesh.js'),
            path.resolve(__dirname, 'x/js/x/graphics/buffer.js'),
            path.resolve(__dirname, 'x/js/x/graphics/complex.js'),
            path.resolve(__dirname, 'x/js/x/graphics/matrix.js'),
            path.resolve(__dirname, 'x/js/x/graphics/obj.js'),
            path.resolve(__dirname, 'x/js/x/graphics/objects.js'),
            path.resolve(__dirname, 'x/js/x/graphics/program.js'),
            path.resolve(__dirname, 'x/js/x/graphics/vector.js'),
            path.resolve(__dirname, 'x/js/x/graphics/vertex.js'),
            path.resolve(__dirname, 'x/js/x/graphics/vertices.js')
          ],
          exclude: /node_modules/,
          use: {
            loader: 'babel-loader',
            options: {
              presets: ['@babel/preset-env']
            }
          }
        }
      ]
    },
    devtool: 'source-map',
    // https://webpack.js.org/concepts/mode/#mode-development
    mode: 'development',
}

module.exports = [ main, homeworld2Worker, matrix ];
