/**
 * 
 * 
 */

import React, { Component } from 'react';

import Strings from '../../util/strings';

import Contextual from '../contextual';

export default class Badge extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            contextual,
            pill,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            "badge",
            Contextual.name('bg', contextual),
            pill && 'rounded-pill',
            className
        ]);

        const props = Object.assign(additional, 
            {}
        );

        return (<span className={classNames} {...props}>{children}</span>);
    }
}