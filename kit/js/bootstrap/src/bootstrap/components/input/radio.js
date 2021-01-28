/**
 * 
 */
import React from 'react';

import Context from '../../context';

import Strings from '../../../util/strings';
import Collections from '../../../util/collections';

export default class Radio extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            inline,
            id,
            ...additional
        } = this.props;

        const form = Collections.find(this.context.type, "form");


        const classNames = Strings.join([
            className,
            form && Strings.join(["form-check", inline && "form-check-inline"])
        ]);

        const props = Object.assign(additional,
            {}
        );
        
        return (
            <div className={classNames}>
                <input type="radio" className="form-check-input" id={id} {...props} />
                {Collections.exist(children) && <label className="form-check-label" htmlFor={id}>{children}</label>}
            </div>
        );
    }
}