import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import Bootstraps from '../../../../util/bootstraps';
import Reacts from '../../../../util/reacts';
import Strings from '../../../../util/strings';
import DropdownCardMenu from './menu';
import Dropdown from '../../dropdown';

export default class DropdownCard extends Dropdown {
    render() {
        const menus = this.props.children ? this.props.children.filter(o => (o.type === DropdownCardMenu)) : null;
        const children = this.props.children ? this.props.children.filter(o => (o.type !== DropdownCardMenu)) : null;
        return (
            <div className={Strings.join(["card", this.props.shadow && "shadow", Bootstraps.mb(this.props.mb)])} >
                {Reacts.display(this.props.title,
                    <div className="card-header d-flex flex-row align-items-center justify-content-between">
                        <h6 className={Strings.join(["m-0", "font-weight-bold", Strings.join(["text", this.props.type], "-")])}>{this.props.title}</h6>
                        <div className="dropdown no-arrow">
                            <a className="dropdown-toggle" href="#" role="button" id="dropdownMenuLink" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false" onClick={this.toggle}>
                                <FontAwesomeIcon icon={["fas", "ellipsis-v"]} size="sm" className="text-gray-400" fixedWidth />
                            </a>
                            {this.state.visible && menus}
                        </div>
                    </div>
                )}
                <div className="card-body">
                    {children}
                </div>
            </div>

        );
    }
}

DropdownCard.Menu = DropdownCardMenu;