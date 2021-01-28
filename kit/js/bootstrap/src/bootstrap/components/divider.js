
import React from 'react';

import Context from '../context';

import Collections from '../../util/collections';
import Strings from '../../util/strings';
import ListItem from './list/item';

export default class Divider extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            ...props
        } = this.props;

        const classNames = Strings.join([
            className,
            Collections.find(this.context.type, "dropdown") && "dropdown-divider"
        ]);

        const listitem = Collections.find(Collections.last(this.context.type), ["nav", "dropdown"]);

        return listitem ? (<ListItem><hr className={classNames} {...props} /></ListItem>)
                        : (<hr className={classNames} {...props} />);
    }
}