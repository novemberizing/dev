import React from 'react';

export default class Content extends React.Component {
    render() {
        return  (
            <div id="content-wrapper" className="d-flex flex-column">
                <div id="content">
                    {this.props.children}
                </div>
            </div>
        );
    }
}