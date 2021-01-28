import React, { Component } from 'react';

import Strings from '../../../util/strings';

export default class CardGroup extends Component {
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
            "card-group"
        ]);

        const props = Object.assign(additional,
            {}
        );
        
        return (<div className={classNames} {...props}>{children}</div>);
    }
}