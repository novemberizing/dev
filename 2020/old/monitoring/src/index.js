/**
 * 
 * @author novemberizing <novemberizing@gmail.com>
 * @since  0.0.1
 */

import './admin.css';
import './custom.css';
import 'bootstrap/dist/css/bootstrap.css';
import '@fortawesome/fontawesome-free/css/all.css';
import React from 'react';
import ReactDOM from 'react-dom';

import { library } from '@fortawesome/fontawesome-svg-core';
import { fab } from '@fortawesome/free-brands-svg-icons';
import { fas } from '@fortawesome/free-solid-svg-icons';

library.add(fab);
library.add(fas);

import Root from './root';

ReactDOM.render(<Root />, document.getElementById('root'));
