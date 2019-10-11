using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;

namespace lab1
{
    public class RouteConfig
    {
        public static void RegisterRoutes(RouteCollection routes)
        {
            routes.IgnoreRoute("{resource}.axd/{*pathInfo}");

            routes.MapRoute(
                name: "StudentIndex",
                url: "students/all",
                defaults: new {
                    controller = "Student",
                    action = "Index"
                }
            );

            routes.MapRoute(
                name: "SearchTel",
                url: "search/telefon/{telefon}",
                defaults: new {
                    controller = "Search",
                    action = "NumarTelefon",
                    telefon = UrlParameter.Optional
                },
                constraints: new {
                    telefon = @"0\d{9}"
                }
            );

            routes.MapRoute(
                name: "SearchCNP",
                url: "search/cnp/{cnp}",
                defaults: new {
                    controller = "Search",
                    action = "CNP",
                    cnp = UrlParameter.Optional
                },
                constraints: new {
                    cnp = @"[1256]\d{12}"
                }
            );

            // Create students
            routes.MapRoute(
                name: "StudentCreate",
                url: "students/create",
                defaults: new {
                    controller = "Student",
                    action = "Create"
                }
            );

            // Read students
            routes.MapRoute(
                name: "StudentRead",
                url: "students/show/{id}",
                defaults: new {
                    controller = "Student",
                    action = "Read"
                }
            );

            // Update student
            routes.MapRoute(
                name: "StudentUpdate",
                url: "students/edit/{id}",
                defaults: new {
                    controller = "Student",
                    action = "Update",
                }
            );

            // Delete student
            routes.MapRoute(
                name: "StudentDelete",
                url: "students/delete/{id}",
                defaults: new {
                    controller = "Student",
                    action = "Delete"
                }
            );

            routes.MapRoute(
                name: "Concatenare",
                url: "concatenare/{param1}/{param2}",
                defaults: new {
                    controller = "Example",
                    action = "Concatenare",
                    param1 = UrlParameter.Optional,
                    param2 = UrlParameter.Optional
                }
            );

            routes.MapRoute(
                name: "Produs",
                url: "produs/{param1}/{param2}",
                defaults: new {
                    controller = "Example",
                    action = "Produs",
                    param2 = UrlParameter.Optional
                }
            );

            routes.MapRoute(
                name: "Operatie",
                url: "operatie/{t1}/{t2}/{op}",
                defaults: new {
                    controller = "Example",
                    action = "Operatie",
                    t1 = UrlParameter.Optional,
                    t2 = UrlParameter.Optional,
                    op = UrlParameter.Optional
                }
            );

            routes.MapRoute(
                name: "Default",
                url: "{controller}/{action}/{id}",
                defaults: new {
                    controller = "Home",
                    action = "Index",
                    id = UrlParameter.Optional
                }
            );

        }
    }
}
