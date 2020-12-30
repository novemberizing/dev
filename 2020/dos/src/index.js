import Dos from './dos';

const dos = new Dos(document.getElementById('dosbox'),
                    document.getElementById('uploader'));

dos.run()
   .then(o => console.log(o))
   .catch(e => console.log(e));

// import dosbox from '@novemberizing/dosbox';

// let canvas = document.createElement('canvas');

// canvas.id = 'dosbox';
// canvas.width = 640;
// canvas.height = 400;
// canvas.tabIndex = -1;

// dosbox.run(canvas)
//       .then(o => console.log(o))
//       .catch(e => console.log(e));
