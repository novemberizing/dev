/**
 * 
 * @author novemberizing <novemberizing@gmail.com>
 * @since  0.0.1
 */

console.log('hello novemberizing');

function hello() {
    let element = document.createElement('div');
    element.innerHTML = 'Hello Novemberizing';
    return element;
}

document.body.appendChild(hello());
