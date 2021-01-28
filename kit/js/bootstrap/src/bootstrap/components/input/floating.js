import React, { Component } from 'react';

import Strings from '../../../util/strings';

export default class Floating extends Component {
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
            "form-floating"
        ]);

        const props = Object.assign(additional,
            {}
        );
        return (<div className={classNames} {...props}>{children}</div>);
    }
}