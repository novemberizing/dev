import React from 'react';
import Alert from './component/alert';
import Badge from './component/badge';
import Button from './component/button';
import Link from './component/basis/link';
import Breadcrumb from './component/breadcrumb';
import Sidebar from './component/ui/sidebar';

export default class Root extends React.Component {
    render() {
        return (
            <div>
                <Sidebar />
            </div>
        );
    }
}
