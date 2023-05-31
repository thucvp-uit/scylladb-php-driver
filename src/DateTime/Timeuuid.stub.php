<?php

/**
* @generate-class-entries
*/
namespace Cassandra {
    /**
     * @strict-properties
     */
    final class Timeuuid implements Value {
        public function __construct(string $uuid = UNKNOWN) {}

        public function type(): Type {}
        public function time(): int {}
        public function version(): int {}
        public function uuid(): string {}

        public function __toString(): string {}
    }
}