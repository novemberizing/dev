import React from 'react';

export default class Link extends React.Component {
    render() {
        return (
            <a href={this.props.href} className={this.props.className}>
                {this.props.children}
            </a>
        );
    }
}