import React from 'react';


export default class PageRow extends React.Component {
    render() {
        return (
            <div className="row">
                {this.props.children}
            </div>
        );
    }
}