import React from 'react';
import Reacts from '../../../util/reacts';

import PageHeader from './header';
import PageRow from './row';

export default class Page extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            title: 'Blank Page'
        };
    }

    render() {
        return (
            <div className="container-fluid">
                {Reacts.display(this.state.title, <PageHeader title={this.state.title} />)}
            </div>
        );
    }
}

Page.Header = PageHeader;
Page.Row = PageRow;