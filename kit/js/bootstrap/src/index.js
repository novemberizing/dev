import 'bootstrap/dist/js/bootstrap.bundle';
import './bootstrap.css';
import './custom.css'

import React, { Component } from 'react';
import ReactDOM from 'react-dom';

import ProcessTopView from './view/process/top';
import DiskSpaceUsageView from "./view/disk/space/usage";

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
                            <DiskSpaceUsageView />
                            <ProcessTopView />
                        </div>
                    </div>
                </div>
            </section>
        );
        
    }
}

ReactDOM.render(<Root />, document.getElementById('root'));
