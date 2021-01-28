import React, { Component } from 'react';
import Strings from '../../../util/strings';

export default class InputText extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            placeholder,
            label,
            id,
            description,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            "form-control"
        ]);

        const props = Object.assign(additional,
            {}
        );
        // <InputText id="btn-group-addon-1" placeholder="Input group example" label="Input group example" description="@" />
        return ([
            description && description.pos !== 'right' ? (<div key={0} id={`${id}-description`} className="input-group-text">{description.text ? description.text : description}</div>) : undefined,
            <input key={1} className={classNames} placeholder={placeholder} id={id} aria-label={label} aria-describedby={description} {...props} />,
            description && description.pos === 'right' ? (<div key={0} id={`${id}-description`} className="input-group-text">{description.text ? description.text : description}</div>) : undefined,
        ]);
    }
}