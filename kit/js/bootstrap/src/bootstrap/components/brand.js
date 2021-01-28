
import React from 'react';

import Context from '../context';

import Strings from '../../util/strings';
import Collections from '../../util/collections';

export default class Brand extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            href,
            type,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            Collections.last(this.context.type, "navbar") && 'navbar-brand'
        ]);

        const props = Object.assign(additional,
            {}
        );

        return (
            type === 'link' ? <a href={href || '#'} className={classNames} {...props}>{children}</a>
                            : <span className={classNames} {...props}>{children}</span>
        );
    }
}