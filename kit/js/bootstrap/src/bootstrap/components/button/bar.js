import React, { Component } from 'react';

import Strings from '../../../util/strings';

export default class ButtonBar extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            label,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            "btn-toolbar"
        ]);

        const props = Object.assign(additional,
            {}
        );
        
        return (<div className={classNames} role="toolbar" aria-label={label} {...props}>{children}</div>);
    }
}