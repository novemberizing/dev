import React from 'react';
import Alert from './component/alert';
import Link from './component/basis/link';

export default class Root extends React.Component {
    render() {
        return (
            <div>
                <Alert type="primary">
                    PRIMARY
                    <Link href="#">Hello world</Link>
                    <div>
                        <a href="#">hello world</a>
                    </div>
                    <a href="#">hello world</a>
                </Alert>
                <Alert type="secondary">SECONDARY</Alert>
                <Alert type="success">SUCCESS</Alert>
                <Alert type="danger">DANGER</Alert>
                <Alert type="warning">WARNING</Alert>
                <Alert type="info">INFO</Alert>
                <Alert type="light">LIGHT</Alert>
                <Alert type="dark">DARK</Alert>
            </div>
        );
    }
}