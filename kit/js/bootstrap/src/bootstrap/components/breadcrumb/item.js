import React, { Component } from 'react';

import Strings from '../../../util/strings';

export default class BreadcrumbItem extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            index,
            href,
            end,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            "breadcrumb-item",
            className,
            end && "active"
        ]);

        const props = Object.assign(additional,
            end ? { 'aria-current': "page" } : undefined
        );

        const elements = end ? children : (<a href={href || '#'}>{children}</a>);

        return (<li className={classNames} {...props}>{elements}</li>);
    }
}