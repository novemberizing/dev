/**
 * 
 */
import React from 'react';

import Context from '../../context';

import Strings from '../../../util/strings';
import Collections from '../../../util/collections';

export default class Range extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            id,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            "form-range"
        ]);

        const props = Object.assign(additional,
            {}
        );
        return ([
            Collections.exist(children) && <label key={0} htmlFor={id} className="form-label">{children}</label>,
            <input key={1} type="range" className={classNames} id={id} {...props}></input>
        ]);
    }
}