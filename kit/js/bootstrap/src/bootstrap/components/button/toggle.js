/**
 * 
 */

import React from 'react';

import Collections from '../../../util/collections';
import Strings from '../../../util/strings';

import Context from '../../context';

export default class Toggle extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            label,
            expanded,
            target,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            Collections.last(this.context.type, "navbar") && "navbar-toggler"
        ]);

        const props = Object.assign(additional,
            {}
        );
{/* <button class="navbar-toggler" type="button"

data-bs-target="#navbarSupportedContent"
aria-controls="navbarSupportedContent">
      <span class="navbar-toggler-icon"></span>
    </button> */}
        return (
            <button type="button"
                    className={classNames}
                    data-bs-toggle="collapse"
                    aria-label={label}
                    aria-expanded={expanded===true}
                    data-bs-target={`#${target}`}
                    aria-controls={target}
                    {...props}>
                {children}
            </button>
        );
    }
}