/**
 * 
 */

import React from 'react';
import Strings from '../../../util/strings';
import Context from '../../context';
import Contextual from '../../contextual';

export default class CheckboxBtn extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            type,
            className,
            contextual,
            children,
            outline,
            id,
            value,
            defaultChecked,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            "btn",
            Contextual.name(outline ? "btn-outline" : "btn", contextual),
            className,
        ]);

        const props = Object.assign(additional,
            {}
        );

        return ([
            <input key={0} type="checkbox" id={id} className="btn-check" autoComplete="off" value={value}  defaultChecked={defaultChecked} />,
            <label key={1} className={classNames} htmlFor={id} {...props}>{children}</label>
        ]);
    }
}