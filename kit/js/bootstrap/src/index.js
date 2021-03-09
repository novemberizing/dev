import 'bootstrap/dist/js/bootstrap.bundle';
import './bootstrap.css';
import './custom.css'

import React, { Component } from 'react';
import ReactDOM from 'react-dom';

import ProcessTopView from './view/process/top';

class Root extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <section className="novemberizing-block">
                <div className="container">
                    <div className="row justify-content-center">
                        <div className="col text-center">
                            <ProcessTopView />
                        </div>
                    </div>
                </div>
            </section>
        );
        
    }
}

ReactDOM.render(<Root />, document.getElementById('root'));
