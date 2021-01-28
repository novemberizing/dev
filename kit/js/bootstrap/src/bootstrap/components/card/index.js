import React from 'react';

import Context from '../../context';
import Contextual from '../../contextual';

import Strings from '../../../util/strings';

export default class Card extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            contextual,
            image,
            border,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            "card",
            Contextual.name("bg", contextual),
            Contextual.name("border", border)
        ]);

        const props = Object.assign(additional, 
            {}
        );

        const context = {
            type: Context.push(this.context.type, "card")
        };

        return (
            <Context.Provider value={context}>
                <div className={classNames} {...props}>
                    {image && !image.bottom && <img src={image.src} alt={image.alt} className="card-img-top" />}
                    {children}
                    {image && image.bottom && <img src={image.src} alt={image.alt} className="card-img-top" />}
                </div>
            </Context.Provider>

        );
    }
}