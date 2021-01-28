/**
 * BOOTSTRAP: ACCORDION
 * 
 */

import React, { Children, Component } from 'react';

import Context from '../../context';

import Strings from '../../../util/strings';
import AccordionItem from './item';

export default class Accordion extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            id,
            flush,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            "accordion",
            flush && "accordion-flush",
            className
        ]);

        const props = Object.assign(additional,
            {}
        );

        const elements = Children.map(children, (child, index) => child.type === AccordionItem ? React.cloneElement(child, {index, id}) : child );

        return (<div className={className} id={id} {...props}>{elements}</div>);
    }
}