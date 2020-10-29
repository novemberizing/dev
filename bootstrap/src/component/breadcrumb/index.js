import React from 'react';
import BreadcrumbItem from './item';

export default class Breadcrumb extends React.Component {
    render() {
        return (
            <nav aria-label="breadcrumb">
                <ol className="breadcrumb">
                    {this.props.children}
                </ol>
            </nav>);
    }
}

Breadcrumb.Item = BreadcrumbItem;