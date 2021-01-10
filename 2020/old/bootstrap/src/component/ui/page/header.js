import React from 'react';

export default class PageHeader extends React.Component {
    render() {
        return (
            <div className="d-sm-flex align-items-center justify-content-between mb-4">
                <h1 className="h3 mb-0 text-gray-800">{this.props.title}</h1>
                {this.props.children}
            </div>
        );
    }
}