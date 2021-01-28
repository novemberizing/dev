/**
 * 
 */

import React, { Component } from 'react';

import Strings from '../../../util/strings';
import Header from '../header';
import Button from '../button';

export default class AccordionItem extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            title,
            index,
            collapse,
            id,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            "accordion-item",
            className
        ]);

        const props = Object.assign(additional,
            {}
        );

        return (
            <div className={classNames}>
                <Header className={Strings.join(["accordion-header", title.className])}
                        id={`${id}-header-${index}`}
                        size={title.size}
                        {...title.props}>
                    <button className={collapse ? "accordion-button" : "accordion-button collapsed"}
                            type="button"
                            data-bs-toggle="collapse"
                            data-bs-target={`#${id}-collapse-${index}`}
                            aria-expanded={collapse ? true : false}
                            aria-controls={`${id}-collapse-${index}`}>
                        {title.value}
                    </button>
                </Header>
                <div id={`${id}-collapse-${index}`}
                     className={collapse ? "accordion-collapse collapse show" : "accordion-collapse collapse"}
                     aria-labelledby={`${id}-header-${index}`}
                     data-bs-parent={`#${id}`}>
                    <div className="accordion-body">
                        {children}
                    </div>
                </div>
            </div>
        );
    }
}