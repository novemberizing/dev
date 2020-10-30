import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';

import Reacts from '../../../util/reacts';

export default class TopbarBtn extends React.Component {
    render() {
        return (
            <button className="btn btn-link rounded-circle mr-3 d-md-none" onClick={this.props.onClick}>
                {Reacts.display(this.props.icon, <FontAwesomeIcon icon={this.props.icon} />)}
            </button>
        );
    }
}