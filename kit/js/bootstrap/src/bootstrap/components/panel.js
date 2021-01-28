
import React from 'react';
import Collections from '../../util/collections';
import Strings from '../../util/strings';

import Context from '../context';

export default class Panel extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            active,
            id,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            "fade",
            Collections.last(this.context.type, "tab") && 'tab-pane',
            active && 'show active'
        ]);

        const props = Object.assign(additional,
            Collections.last(this.context.type, "tab") ? { role: "tabpanel", "aria-labelledby": `${id}-tab` } : undefined
        );
        return (
            <div id={id} className={classNames} {...props}>{children}</div>
        );
    }
}