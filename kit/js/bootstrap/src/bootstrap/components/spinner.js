/**
 * 
 */
import React, { Component } from 'react';

import Strings from '../../util/strings';
import Breakpoint from '../breakpoint';

import Contextual from '../contextual';

export default class Spinner extends Component {
    static get sm(){ return Breakpoint.sm; }
    static get lg(){ return Breakpoint.lg; }
    static size(type, grow) {
        switch(type) {
            case Spinner.sm: return Breakpoint.name(grow ? 'spinner-grow' : 'spinner-border', type);
            case Spinner.lg: return Breakpoint.name(grow ? 'spinner-grow' : 'spinner-border', type);
        }
        return undefined;
    }
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            label,
            color,
            grow,
            size,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            grow ? "spinner-grow" : "spinner-border",
            Contextual.name('text', color),
            Spinner.size(size, grow)
        ]);

        const props = Object.assign(additional,
            {}
        );

        return (
            <div className={classNames} role="status" {...props}>
                {label && <span className="visually-hidden">{label}</span>}
                {children}
            </div>
        );
    }
}