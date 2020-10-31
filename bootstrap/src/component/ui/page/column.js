import React from 'react';
import Bootstraps from '../../../util/bootstraps';

export default class PageColumn extends React.Component {
    render() {
        return (
            <div className={Bootstraps.lg('col', 6)}>
                {this.props.children}
            </div>
        );
    }
}