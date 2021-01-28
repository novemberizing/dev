/**
 * 
 */
import React, { Component } from 'react';

import Strings from '../../../util/strings';

export default class Progress extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            "progress"
        ]);

        const props = Object.assign(additional,
            {}
        );

        return (<div className={classNames} {...props}>{children}</div>);
        
    }
}