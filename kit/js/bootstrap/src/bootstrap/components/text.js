import React from 'react';
import Collections from '../../util/collections';
import Strings from '../../util/strings';

import Context from '../context';

export default class Text extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            ...additional
        } = this.props;

        const parent = Collections.last(this.context.type);

        const classNames = Strings.join([
            className,
            parent === "navbar" && 'navbar-text',
            Collections.find(this.context.type, "form") && 'form-text'
        ]);

        const props = Object.assign(additional,
            {}
        );
        
        return (<span className={classNames} {...props}>{children}</span>);
    }
}