<?php

/**
 * @file
 * Lagoon Drupal 7 configuration file.
 *
 * You should not edit this file, please use environment specific files!
 * They are loaded in this order:
 * - settings.all.php
 *   For settings that should be applied to all environments (dev, prod, staging, docker, etc).
 * - settings.production.php
 *   For settings only for the production environment.
 * - settings.development.php
 *   For settings only for the development environment (dev servers, docker).
 * - settings.local.php
 *   For settings only for the local environment, this file will not be commited in GIT!
 *
 */

 ### Lagoon Database connection
 $mariadb_port = preg_replace('/.*:(\d{2,5})$/', '$1', getenv('MARIADB_PORT') ?: '3306'); // Kubernetes/OpenShift sets `*_PORT` by default as tcp://172.30.221.159:8983, extract the port from it
 $db_url = sprintf("mysqli://%s:%s@%s:%s/%s", 
    getenv('MARIADB_USERNAME') ?: 'drupal', 
    getenv('MARIADB_PASSWORD') ?: 'drupal',
    getenv('MARIADB_HOST') ?: 'mariadb',
    $mariadb_port,
    getenv('MARIADB_DATABASE') ?: 'drupal');


### Lagoon Varnish & reverse proxy settings
if (getenv('LAGOON')) {
  $varnish_control_port = getenv('VARNISH_CONTROL_PORT') ?: '6082';
  $varnish_hosts = explode(',', getenv('VARNISH_HOSTS') ?: 'varnish');
  array_walk($varnish_hosts, function(&$value, $key) use ($varnish_control_port) { $value .= ":$varnish_control_port"; });

  $conf['reverse_proxy'] = TRUE;
  $conf['reverse_proxy_addresses'] = array_merge(explode(',', getenv('VARNISH_HOSTS')), array('varnish'));
  $conf['varnish_control_terminal'] = implode($varnish_hosts, " ");
  $conf['varnish_control_key'] = getenv('VARNISH_SECRET') ?: 'lagoon_default_secret';
  $conf['varnish_version'] = 4;

}

### Base URL
if (getenv('LAGOON_ROUTES')) {
  $routes = explode(',', getenv('LAGOON_ROUTES'));
  $base_url = $routes[0];
}

### Temp directory
if (getenv('TMP')) {
  $conf['file_temporary_path'] = getenv('TMP');
}

### Hash Salt
if (getenv('LAGOON')){
  $drupal_hash_salt = hash('sha256', getenv('LAGOON_PROJECT'));
}

// Loading settings for all environment types.
if (file_exists(__DIR__ . '/all.settings.php')) {
  include __DIR__ . '/all.settings.php';
}

// Environment specific settings files.
if(getenv('LAGOON_ENVIRONMENT_TYPE')){
  if (file_exists(__DIR__ . '/' . getenv('LAGOON_ENVIRONMENT_TYPE') . '.settings.php')) {
    include __DIR__ . '/' . getenv('LAGOON_ENVIRONMENT_TYPE') . '.settings.php';
  }
}

// Last: this servers specific settings files.
if (file_exists(__DIR__ . '/settings.local.php')) {
  include __DIR__ . '/settings.local.php';
}
